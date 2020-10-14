#ifndef DJPYTHIA_DATA_MODEL_ORIGIN_H_
#define DJPYTHIA_DATA_MODEL_ORIGIN_H_

namespace djpythia {
namespace data_model {

/* Enumerator that stores if the particle is produced by charm or beauty quarks.
 * In case the particle comes from other source, it should be marked as kNone.
 */
enum class HFSource { kCharm=4, kBeauty=5, kNone=-1};
} // namespace data_model
} // namespace djpythia

#endif // DJPYTHIA_DATA_MODEL_ORIGIN_H_
