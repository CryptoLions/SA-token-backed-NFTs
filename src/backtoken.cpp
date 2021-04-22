#include <backtoken.hpp>

const name SIMPLEASSETS_CONTRACT = "simpleassets"_n; // SimpleAssets CONTRACT

ACTION backtoken::getversion() {
	check(false, "Version number 1.0.2, Build date: 2021-01-04 13:40");
}

#ifdef DEBUG
ACTION backtoken::delbtoken(uint64_t nft_id)
{
	require_auth(get_self());
	const auto itr_backtoken = backtokent.require_find(nft_id, string("asset id: " + to_string(nft_id) + " was not found in backtokens table. Prepare token before send it").c_str());
	backtokent.erase(itr_backtoken);
}
#endif

ACTION backtoken::tokenprep(name owner, uint64_t nft_id, const vector<backtoken::symbol_ex>& symbols)
{
	require_auth(owner);

	const auto itr = backtokent.find(nft_id);

	if (itr == backtokent.end())
	{
		backtokent.emplace(_self, [&](auto& s) {
			s.nft_id = nft_id;
			s.prepare_tokens(symbols);
		});
	}
	else {
		backtokent.modify(itr, get_self(), [&](auto& s) {
			s.prepare_tokens(symbols);
		});
	}
}

ACTION backtoken::onburn(name owner, uint64_t nft_id)
{
	require_auth(SIMPLEASSETS_CONTRACT);
	const auto itr_backtoken = backtokent.require_find(nft_id, string("asset id: " + to_string(nft_id) + " was not found in backtokens table. Prepare token before send it").c_str());

	send_tokens(owner, itr_backtoken->tokens, string("Asset id " + to_string(nft_id) + " was burnt"));

	backtokent.erase(itr_backtoken);
}

void backtoken::send_tokens(name owner, const vector<backtoken::token_ex>& tokens, string memo)
{
	vector<uint64_t> assetids;
	for (auto it = tokens.begin(); it != tokens.end(); it++)
	{
		if (it->is_token())
		{
			if (it->get_amount() <= 0) {
				continue;
			}

			action(
				permission_level{ get_self(),"active"_n },
				it->get_contract(),
				"transfer"_n,
				make_tuple(get_self(), owner, it->get_quantity(), memo)
			).send();
		}
		else if (it->is_nft())
		{
			if (!it->is_token_valid()){
				continue;
			}

			assetids.push_back(it->token_id);
		}
		else if (it->is_ft())
		{
			if (it->get_amount() <= 0) {
				continue;
			}

			action(
				permission_level{ get_self(),"active"_n },
				SIMPLEASSETS_CONTRACT,
				"transferf"_n,
				make_tuple(get_self(), owner, it->get_contract(), it->get_quantity(), memo)
			).send();
		}
	}

	if (!assetids.empty()) {

		action(
			permission_level{ get_self(), "active"_n },
			SIMPLEASSETS_CONTRACT,
			"offer"_n,
			make_tuple(get_self(), owner, assetids, memo)
		).send();
	}
}

void backtoken::ontransfersa(name from, name to, vector<uint64_t>& assetids, string memo) {
	if (to != get_self() || from == get_self()) {
		return;
	}

	require_auth(from);
	require_recipient(from);
	
	for (auto it = assetids.begin(); it != assetids.end(); it++)
	{
		check(!(backtokent.find(*it) != backtokent.end()), 
			"Token id = " + to_string(*it) + " already have back tokens assigned to it");
	}

	const auto tokens = token_ex::nfts_to_tokenexs(assetids);

	process_memo(from, to, tokens, memo);
}

void backtoken::ontransferf(name from, name to, name author, asset quantity, string memo)
{
	if (to != get_self() || from == get_self()) {
		return;
	}

	require_auth(from);

	const auto tokens = token_ex::ft_to_tokenexs(author, quantity);

	process_memo(from, to, tokens, memo);
}

void backtoken::ontransfer(name from, name to, asset quantity, string memo)
{
	if (to != get_self()) {
		return;
	}

	require_auth(from);

	const auto tokens = token_ex::token_to_tokenexs(get_first_receiver(), quantity);

	process_memo(from, to, tokens, memo);
}

void backtoken::process_memo(name from, name to, const vector<token_ex> & tokens, const string& memo)
{
	const uint64_t nft_id = atoll(memo.c_str());

	SimpleAssets::sassets assets(SIMPLEASSETS_CONTRACT, from.value);
	const auto itr = assets.require_find(nft_id, string("asset id: " + to_string(nft_id) + " was not found").c_str());

	check(!(itr->owner.value != from.value), 
		"You are not owner of asset id: " + to_string(nft_id) + " . Owner is " + itr->owner.to_string());

	const auto itr_backtoken = backtokent.require_find(nft_id, string("Asset id: " + to_string(nft_id) + " was not found in backtokens table. Prepare token before send it").c_str());

	backtokent.modify(itr_backtoken, get_self(), [&](auto& s) {
		s.append_tokens(tokens);
	});

	SEND_INLINE_ACTION(*this, ontransferlog, { {_self, "active"_n} }, { from, to, tokens, memo });

}
